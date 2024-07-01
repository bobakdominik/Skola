using Microsoft.EntityFrameworkCore;
using System.Data.Common;

namespace medicinska_informatika_SP.Data
{
    public class PDSOutputsService
    {
        private readonly ApplicationDbContext _context;

        public PDSOutputsService(ApplicationDbContext context)
        {
            _context = context;
        }

        public DbConnection GetDbConnection()
        {
            return _context.Database.GetDbConnection();
        }
    }
}
