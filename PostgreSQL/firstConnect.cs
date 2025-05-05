using System;
using Npgsql;
namespace TestJ
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var connString = "Host=;Username=;Password=;Database=person_tasks";

            using (var conn = new NpgsqlConnection(connString))
            {
                conn.Open();

                using (var cmd = new NpgsqlCommand("SELECT version()", conn))
                using (var reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        Console.WriteLine($"PostgreSQL version: {reader.GetString(0)}");
                        
                    }
                }
            }
            Console.ReadLine();
        }
    }
}
