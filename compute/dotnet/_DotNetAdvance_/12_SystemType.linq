<Query Kind="Statements" />

using System;

Type t = typeof(int); 
t.GetMethods().Dump();

Type t2 ="hello".GetType();
t2.FullName.Dump();
t2.GetFields().Dump();
t2.GetMethods().Dump();
var a=typeof (string).Assembly.Dump();
a.GetTypes().Dump();

var t3 = Type.GetType("System.Int64");
t3.FullName.Dump();
t3.GetFields().Dump();
t3.GetMethods().Dump();

var t4 = Type.GetType("System.Collections.Generic.List`1");
t4.FullName.Dump();
t4.GetFields().Dump();
t4.GetMethods().Dump();

