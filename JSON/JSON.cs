using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

public class PersonNote
{
    public int userId { get; set; }
    public string userName { get; set; }
    public int noteId { get; set; }
    public List<string> taskStage { get; set; }
}

internal class Program
{
    static void Main(string[] args)
    {
        var tasks = new List<PersonNote> {
            new PersonNote
            {
                userId =1,
                userName = "Rin",
                noteId = 1,
                taskStage = new List<string>{"task1","task2", "task3"}
            },
            new PersonNote
            {
                userId=2,
                userName = "Max",
                noteId = 1,
                taskStage = new List<string>{"programming"}
            }
        };

        string jsonString = JsonSerializer.Serialize(tasks, new JsonSerializerOptions
        {
            WriteIndented = true
        });

        string filePath = "tasks.json";
        File.WriteAllText(filePath, jsonString);

        Console.WriteLine("Содержимое JSON:", jsonString);

    }
}

   