using medicinska_informatika_SP.Data.Models;
using Microsoft.EntityFrameworkCore;

namespace medicinska_informatika_SP.Data
{
    public class TestujemeService
    {
        private readonly ApplicationDbContext _context;

        public TestujemeService(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IEnumerable<TestTabulka>> GetForecastAsync()
        {
            // Zoberie asynchronne await metoda musi byt async
            return await _context.TestTabulka.ToListAsync();
        }
    }
}