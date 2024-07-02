<Query Kind="Statements" />

using System;

var t = typeof(bool);
var b = Activator.CreateInstance(t);
b.Dump();

var b2 = Activator.CreateInstance<bool>();
b2.Dump();

var wc = Activator.CreateInstance("System", "System.Timers.Timer");
wc.Dump();
wc.Unwrap().Dump();

var alType = Type.GetType("System.Collections.ArrayList");
alType.Dump();
var alCtor = alType.GetConstructor(Array.Empty<Type>());
alCtor.Dump();

var al = alCtor.Invoke(Array.Empty<object>());
al.Dump();

var st = typeof(string);
var ctor = st.GetConstructor(new[] { typeof(char[]) });
ctor.Dump();
var str = ctor.Invoke(new object[] { new[] { 't', 'e', 's', 't' } });
str.Dump();


var listType = Type.GetType("System.Collections.Generic.List`1");
listType.Dump();
var listOfIntType = listType.MakeGenericType(typeof(int));
listOfIntType.Dump();

var listOfIntCtor = listOfIntType.GetConstructor(Array.Empty<Type>());
listOfIntCtor.Dump();
var theList = listOfIntCtor.Invoke(Array.Empty<object>());
theList.Dump();

var charType = typeof(char);
Array.CreateInstance(charType, 10);
var charArrayType = charType.MakeArrayType();
charArrayType.FullName.Dump();

var charArrayCtor = charArrayType.GetConstructor(new[] { typeof(int) });
charArrayCtor.Dump();
var arr=charArrayCtor.Invoke(new object[] {20});
arr.Dump();


