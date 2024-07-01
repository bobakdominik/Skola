using medicinska_informatika_SP.Data.Models;
using Microsoft.EntityFrameworkCore;
using System.Data.Common;

namespace medicinska_informatika_SP.Data
{
    public interface IRoleService
    {
        DbConnection getDbConnection();
        Task<IEnumerable<Role>> GetRole();
        Role GetRoleForUser(Employee user);
        Role GetRoleByID(int id);
    };

    public class RoleService : IRoleService
    {
        private readonly ApplicationDbContext _context;

        public RoleService(ApplicationDbContext context)
        {
            _context = context;
        }

        public DbConnection getDbConnection()
        {
            return _context.Database.GetDbConnection();
        }

        public async Task<IEnumerable<Role>> GetRole()
        {
            // Zoberie asynchronne await metoda musi byt async
            return await _context.Roles.ToListAsync();
        }

        public Role GetRoleByID(int id)
        {
            var roles = _context.Roles;
            return roles.First(e => e.IDRola == id);
        }

        public Role GetRoleForUser(Employee user)
        {
            return _context.Roles.FirstOrDefault(e => e.Personal == user.EmployeeId);
        }
    }
}