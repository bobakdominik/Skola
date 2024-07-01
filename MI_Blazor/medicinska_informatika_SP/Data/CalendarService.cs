using Microsoft.EntityFrameworkCore;
using System.Data.Common;

namespace medicinska_informatika_SP.Data
{
    public class CalendarSercice
    {
        private readonly ApplicationDbContext _context;

        public CalendarSercice(ApplicationDbContext context)
        {
            _context = context;
        }

        public DbConnection getDbConnection()
        {
            return _context.Database.GetDbConnection();
        }
    }
}