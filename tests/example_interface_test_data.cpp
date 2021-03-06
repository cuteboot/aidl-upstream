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

#include "tests/test_data.h"

namespace aidl {
namespace test_data {

const char kIExampleInterfaceClass[] = "android.test.IExampleInterface";

const char* kIExampleInterfaceParcelables[] = {
  "android.foo.ExampleParcelable",
  nullptr,
};

const char* kIExampleInterfaceInterfaces[] = {
  "android.bar.IAuxInterface",
  "android.test.IAuxInterface2",
  nullptr,
};

const char kIExampleInterfaceContents[] = R"(
package android.test;

import android.foo.ExampleParcelable;
import android.test.CompoundParcelable;
import android.bar.IAuxInterface;
import android.test.IAuxInterface2;

interface IExampleInterface {
    boolean isEnabled();
    int getState();
    String getAddress();

    /* Test long comment */
    ExampleParcelable[] getParcelables();

    // Test short comment
    boolean setScanMode(int mode, int duration);

    /* Test long comment */
    // And short comment
    void registerBinder(IAuxInterface foo);
    IExampleInterface getRecursiveBinder();

    int takesAnInterface(in IAuxInterface2 arg);
    int takesAParcelable(in CompoundParcelable.Subclass1 arg,
                         inout CompoundParcelable.Subclass2 arg2);
}
)";

const char kIExampleInterfaceDeps[] =
R"(android/test/IExampleInterface.java: \
  android/test/IExampleInterface.aidl \
  ./android/foo/ExampleParcelable.aidl \
  ./android/test/CompoundParcelable.aidl \
  ./android/bar/IAuxInterface.aidl \
  ./android/test/IAuxInterface2.aidl

android/test/IExampleInterface.aidl :
./android/foo/ExampleParcelable.aidl :
./android/test/CompoundParcelable.aidl :
./android/bar/IAuxInterface.aidl :
./android/test/IAuxInterface2.aidl :
)";

const char kIExampleInterfaceJava[] =
R"(/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: android/test/IExampleInterface.aidl
 */
package android.test;
public interface IExampleInterface extends android.os.IInterface
{
/** Local-side IPC implementation stub class. */
public static abstract class Stub extends android.os.Binder implements android.test.IExampleInterface
{
private static final java.lang.String DESCRIPTOR = "android.test.IExampleInterface";
/** Construct the stub at attach it to the interface. */
public Stub()
{
this.attachInterface(this, DESCRIPTOR);
}
/**
 * Cast an IBinder object into an android.test.IExampleInterface interface,
 * generating a proxy if needed.
 */
public static android.test.IExampleInterface asInterface(android.os.IBinder obj)
{
if ((obj==null)) {
return null;
}
android.os.IInterface iin = obj.queryLocalInterface(DESCRIPTOR);
if (((iin!=null)&&(iin instanceof android.test.IExampleInterface))) {
return ((android.test.IExampleInterface)iin);
}
return new android.test.IExampleInterface.Stub.Proxy(obj);
}
@Override public android.os.IBinder asBinder()
{
return this;
}
@Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
{
switch (code)
{
case INTERFACE_TRANSACTION:
{
reply.writeString(DESCRIPTOR);
return true;
}
case TRANSACTION_isEnabled:
{
data.enforceInterface(DESCRIPTOR);
boolean _result = this.isEnabled();
reply.writeNoException();
reply.writeInt(((_result)?(1):(0)));
return true;
}
case TRANSACTION_getState:
{
data.enforceInterface(DESCRIPTOR);
int _result = this.getState();
reply.writeNoException();
reply.writeInt(_result);
return true;
}
case TRANSACTION_getAddress:
{
data.enforceInterface(DESCRIPTOR);
java.lang.String _result = this.getAddress();
reply.writeNoException();
reply.writeString(_result);
return true;
}
case TRANSACTION_getParcelables:
{
data.enforceInterface(DESCRIPTOR);
android.foo.ExampleParcelable[] _result = this.getParcelables();
reply.writeNoException();
reply.writeTypedArray(_result, android.os.Parcelable.PARCELABLE_WRITE_RETURN_VALUE);
return true;
}
case TRANSACTION_setScanMode:
{
data.enforceInterface(DESCRIPTOR);
int _arg0;
_arg0 = data.readInt();
int _arg1;
_arg1 = data.readInt();
boolean _result = this.setScanMode(_arg0, _arg1);
reply.writeNoException();
reply.writeInt(((_result)?(1):(0)));
return true;
}
case TRANSACTION_registerBinder:
{
data.enforceInterface(DESCRIPTOR);
android.bar.IAuxInterface _arg0;
_arg0 = android.bar.IAuxInterface.Stub.asInterface(data.readStrongBinder());
this.registerBinder(_arg0);
reply.writeNoException();
return true;
}
case TRANSACTION_getRecursiveBinder:
{
data.enforceInterface(DESCRIPTOR);
android.test.IExampleInterface _result = this.getRecursiveBinder();
reply.writeNoException();
reply.writeStrongBinder((((_result!=null))?(_result.asBinder()):(null)));
return true;
}
case TRANSACTION_takesAnInterface:
{
data.enforceInterface(DESCRIPTOR);
android.test.IAuxInterface2 _arg0;
_arg0 = android.test.IAuxInterface2.Stub.asInterface(data.readStrongBinder());
int _result = this.takesAnInterface(_arg0);
reply.writeNoException();
reply.writeInt(_result);
return true;
}
case TRANSACTION_takesAParcelable:
{
data.enforceInterface(DESCRIPTOR);
android.test.CompoundParcelable.Subclass1 _arg0;
if ((0!=data.readInt())) {
_arg0 = android.test.CompoundParcelable.Subclass1.CREATOR.createFromParcel(data);
}
else {
_arg0 = null;
}
android.test.CompoundParcelable.Subclass2 _arg1;
if ((0!=data.readInt())) {
_arg1 = android.test.CompoundParcelable.Subclass2.CREATOR.createFromParcel(data);
}
else {
_arg1 = null;
}
int _result = this.takesAParcelable(_arg0, _arg1);
reply.writeNoException();
reply.writeInt(_result);
if ((_arg1!=null)) {
reply.writeInt(1);
_arg1.writeToParcel(reply, android.os.Parcelable.PARCELABLE_WRITE_RETURN_VALUE);
}
else {
reply.writeInt(0);
}
return true;
}
}
return super.onTransact(code, data, reply, flags);
}
private static class Proxy implements android.test.IExampleInterface
{
private android.os.IBinder mRemote;
Proxy(android.os.IBinder remote)
{
mRemote = remote;
}
@Override public android.os.IBinder asBinder()
{
return mRemote;
}
public java.lang.String getInterfaceDescriptor()
{
return DESCRIPTOR;
}
@Override public boolean isEnabled() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
boolean _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_isEnabled, _data, _reply, 0);
_reply.readException();
_result = (0!=_reply.readInt());
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
@Override public int getState() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
int _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getState, _data, _reply, 0);
_reply.readException();
_result = _reply.readInt();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
@Override public java.lang.String getAddress() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
java.lang.String _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getAddress, _data, _reply, 0);
_reply.readException();
_result = _reply.readString();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/* Test long comment */
@Override public android.foo.ExampleParcelable[] getParcelables() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
android.foo.ExampleParcelable[] _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getParcelables, _data, _reply, 0);
_reply.readException();
_result = _reply.createTypedArray(android.foo.ExampleParcelable.CREATOR);
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
// Test short comment

@Override public boolean setScanMode(int mode, int duration) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
boolean _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeInt(mode);
_data.writeInt(duration);
mRemote.transact(Stub.TRANSACTION_setScanMode, _data, _reply, 0);
_reply.readException();
_result = (0!=_reply.readInt());
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/* Test long comment */// And short comment

@Override public void registerBinder(android.bar.IAuxInterface foo) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeStrongBinder((((foo!=null))?(foo.asBinder()):(null)));
mRemote.transact(Stub.TRANSACTION_registerBinder, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
@Override public android.test.IExampleInterface getRecursiveBinder() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
android.test.IExampleInterface _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getRecursiveBinder, _data, _reply, 0);
_reply.readException();
_result = android.test.IExampleInterface.Stub.asInterface(_reply.readStrongBinder());
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
@Override public int takesAnInterface(android.test.IAuxInterface2 arg) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
int _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeStrongBinder((((arg!=null))?(arg.asBinder()):(null)));
mRemote.transact(Stub.TRANSACTION_takesAnInterface, _data, _reply, 0);
_reply.readException();
_result = _reply.readInt();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
@Override public int takesAParcelable(android.test.CompoundParcelable.Subclass1 arg, android.test.CompoundParcelable.Subclass2 arg2) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
int _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
if ((arg!=null)) {
_data.writeInt(1);
arg.writeToParcel(_data, 0);
}
else {
_data.writeInt(0);
}
if ((arg2!=null)) {
_data.writeInt(1);
arg2.writeToParcel(_data, 0);
}
else {
_data.writeInt(0);
}
mRemote.transact(Stub.TRANSACTION_takesAParcelable, _data, _reply, 0);
_reply.readException();
_result = _reply.readInt();
if ((0!=_reply.readInt())) {
arg2.readFromParcel(_reply);
}
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
}
static final int TRANSACTION_isEnabled = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
static final int TRANSACTION_getState = (android.os.IBinder.FIRST_CALL_TRANSACTION + 1);
static final int TRANSACTION_getAddress = (android.os.IBinder.FIRST_CALL_TRANSACTION + 2);
static final int TRANSACTION_getParcelables = (android.os.IBinder.FIRST_CALL_TRANSACTION + 3);
static final int TRANSACTION_setScanMode = (android.os.IBinder.FIRST_CALL_TRANSACTION + 4);
static final int TRANSACTION_registerBinder = (android.os.IBinder.FIRST_CALL_TRANSACTION + 5);
static final int TRANSACTION_getRecursiveBinder = (android.os.IBinder.FIRST_CALL_TRANSACTION + 6);
static final int TRANSACTION_takesAnInterface = (android.os.IBinder.FIRST_CALL_TRANSACTION + 7);
static final int TRANSACTION_takesAParcelable = (android.os.IBinder.FIRST_CALL_TRANSACTION + 8);
}
public boolean isEnabled() throws android.os.RemoteException;
public int getState() throws android.os.RemoteException;
public java.lang.String getAddress() throws android.os.RemoteException;
/* Test long comment */
public android.foo.ExampleParcelable[] getParcelables() throws android.os.RemoteException;
// Test short comment

public boolean setScanMode(int mode, int duration) throws android.os.RemoteException;
/* Test long comment */// And short comment

public void registerBinder(android.bar.IAuxInterface foo) throws android.os.RemoteException;
public android.test.IExampleInterface getRecursiveBinder() throws android.os.RemoteException;
public int takesAnInterface(android.test.IAuxInterface2 arg) throws android.os.RemoteException;
public int takesAParcelable(android.test.CompoundParcelable.Subclass1 arg, android.test.CompoundParcelable.Subclass2 arg2) throws android.os.RemoteException;
}
)";

}  // namespace test_data
}  // namespace aidl
