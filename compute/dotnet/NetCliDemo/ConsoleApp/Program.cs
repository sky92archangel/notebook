// See https://aka.ms/new-console-template for more information

using Newtonsoft.Json;



#if DEBUG
Console.WriteLine("Hello, World! debug");
#else
Console.WriteLine("Hello, World! release");
#endif

var student = new Student(1, "sfe", "A");
var json = JsonConvert.SerializeObject(student);
Console.WriteLine(json);

public class Student
{

    public Student(int _id, string _name, string _grade)
    {
        this.id = _id;
        this.name = _name;
        this.grade = _grade;
    }
    public int id { get; set; }
    public string name { get; set; }
    public string grade { get; set; }
}


public record Teacher(int Id,string Name , string Class );