using medicinska_informatika_SP.Data.Models;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using System.Data.Common;
using System.Xml.Linq;

namespace medicinska_informatika_SP.Data
{
    public interface IEmployeService
    {
        DbConnection getDbConnection();
        Task<IEnumerable<Employee>> GetEmployees();
        Employee GetEmployeeByID(int id);
        Employee GetEmployeeByName(string name);
        bool checkLogin(string password, string username);
    };

    public class EmployeService : IEmployeService
    {
        private readonly ApplicationDbContext _context;

        public EmployeService(ApplicationDbContext context)
        {
            _context = context;
        }

        public DbConnection getDbConnection()
        {
            return _context.Database.GetDbConnection();
        }

        public async Task<IEnumerable<Employee>> GetEmployees()
        {
            // Zoberie asynchronne await metoda musi byt async
            return await _context.Employee.ToListAsync();
        }

        public Employee GetEmployeeByID(int id)
        {
            var employees = _context.Employee;
            return employees.FirstOrDefault(e => e.EmployeeId == id);
        }

        public Employee GetEmployeeByName(string name)
        {
            var employees = _context.Employee;
            return employees.FirstOrDefault(e => e.Username.ToUpper() == name);
        }

        public bool checkLogin(string password, string username)
        {
            var user = _context.Employee.First(e => e.Username.ToUpper() == username);
            var result = BCrypt.Net.BCrypt.Verify(password, user.Password);
            return result;
        }
    }
}