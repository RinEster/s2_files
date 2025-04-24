using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

//работа с сложными объектами

public class Person
{
    public int userId { get; set; }
    public string userName { get; set; }    
    public List<Task> tasks { get; set; }
}


public class Task 
{
    public int taskId { get; set; }
    public string taskName { get; set; }
    public List<string> taskStages { get; set; }
}


internal class Program
{
    static void Main(string[] args)
    {

        var peopleAndTasks = new Person
        {
            userId = 1,
            userName = "Rin",
            tasks = new List<Task>()
            {
                new Task
                {
                    taskId = 1,
                    taskName = "Test",
                    taskStages = new List<string>{"task1", "task2", "task3" }
                },
                new Task
                {
                    taskId= 2,
                    taskName = "Test2",
                    taskStages = new List<string>{"one","two"}
                }
                
            }

        };




        string jsonString = JsonSerializer.Serialize(peopleAndTasks, new JsonSerializerOptions
        {
            WriteIndented = true
        });


        string filePath = "rinTasks.json";
        File.WriteAllText(filePath, jsonString);


        Console.ReadLine();
    }
}

