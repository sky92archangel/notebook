<Query Kind="Statements">
  <Namespace>System.Numerics</Namespace>
  <RuntimeVersion>7.0</RuntimeVersion>
</Query>

byte[] array1 = Enumerable.Range(1, 128).Select(x => (byte)x).ToArray();
byte[] array2 = Enumerable.Range(4, 128).Select(x => (byte)x).ToArray();
byte[] result = new byte[128];
int size = System.Numerics.Vector<byte>.Count;

array1.Dump();
array2.Dump();
size.Dump();
for (int i = 0; i < array1.Length; i+=size)
{
	var va =new Vector<byte>(array1,i);
	var vb =new Vector<byte>(array2,i);
	var vresult =va+vb;
	vresult.CopyTo(result,i);
	vresult.Dump();
}


