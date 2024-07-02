<Query Kind="Statements" />


using System;

var  t = typeof	(Guid);
t.FullName.Dump();
t.Name.Dump();

var ctors = t.GetConstructors();
ctors.Dump(); 
ctors.First().GetParameters().Dump();

