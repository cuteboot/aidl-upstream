/*
 * Copyright (C) 2015, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fake_io_delegate.h"

#include <base/files/file_path.h>
#include <base/stringprintf.h>

#include "os.h"
#include "tests/test_util.h"

using android::base::StringAppendF;
using android::base::StringPrintf;
using base::FilePath;
using std::string;
using std::unique_ptr;
using std::vector;

namespace android {
namespace aidl {
namespace test {

unique_ptr<string> FakeIoDelegate::GetFileContents(
    const string& relative_filename,
    const string& content_suffix) const {
  string filename = CleanPath(relative_filename);
  unique_ptr<string> contents;
  auto it = file_contents_.find(filename);
  if (it == file_contents_.end()) {
    return contents;
  }
  contents.reset(new string);
  *contents = it->second;
  contents->append(content_suffix);

  return contents;
}

bool FakeIoDelegate::FileIsReadable(const string& path) const {
  return file_contents_.find(CleanPath(path)) != file_contents_.end();
}

void FakeIoDelegate::SetFileContents(const string& filename,
                                     const string& contents) {
  file_contents_[filename] = contents;
}

void FakeIoDelegate::AddStubParcelable(const string& canonical_name) {
  AddStub(canonical_name, "package %s;\nparcelable %s;");
}

void FakeIoDelegate::AddStubInterface(const string& canonical_name) {
  AddStub(canonical_name, "package %s;\ninterface %s { }");
}

void FakeIoDelegate::AddCompoundParcelable(const string& canonical_name,
                                           const vector<string>& subclasses) {
  string package, class_name;
  FilePath rel_path;
  SplitPackageClass(canonical_name, &rel_path, &package, &class_name);
  string contents = StringPrintf("package %s;\n", package.c_str());
  for (const string& subclass : subclasses) {
    StringAppendF(&contents, "parcelable %s.%s;\n",
                  class_name.c_str(), subclass.c_str());
  }
  SetFileContents(rel_path.value(), contents);
}

void FakeIoDelegate::AddStub(const string& canonical_name,
                             const char* format_str) {
  string package, class_name;
  FilePath rel_path;
  SplitPackageClass(canonical_name, &rel_path, &package, &class_name);
  SetFileContents(
      rel_path.value(),
      StringPrintf(format_str, package.c_str(), class_name.c_str()));
}

string FakeIoDelegate::CleanPath(const string& path) const {
  string clean_path = path;
  while (clean_path.length() >= 2 &&
         clean_path[0] == '.' &&
         clean_path[1] == OS_PATH_SEPARATOR) {
    clean_path = clean_path.substr(2);
  }
  return clean_path;
}

}  // namespace test
}  // namespace android
}  // namespace aidl
