using medicinska_informatika_SP.Data.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using System.Data.Common;

namespace medicinska_informatika_SP.Data
{
    public class PatientCardsService
    {
        private readonly ApplicationDbContext _context;

        public PatientCardsService(ApplicationDbContext context)
        {
            _context = context;
        }

        public DbConnection GetDbConnection()
        {
            return _context.Database.GetDbConnection();
        }

        public async Task<IEnumerable<BlobData>> GetBlobDataAsync()
        {
            return await _context.BlobDatas.ToListAsync();
        }

        public async Task<IEnumerable<Document>> GetDocumentAsync()
        {
            return await _context.Documents.ToListAsync();
        }

        public async Task<IEnumerable<Person>> GetPersonsAsync()
        {
            return await _context.Persons.ToListAsync();
        }

        public async Task<IEnumerable<Illness>> GetIllnessesAsync()
        {
            return await _context.Illnesses.ToListAsync();
        }

        public async Task<IEnumerable<Vaccination>> GetVaccinationsAsync()
        {
            return await _context.Vaccinations.ToListAsync();
        }

        public void AddIllnessToDb(Illness illness)
        {
            _context.Add(illness);
        }

        public void AddIllnessListToDb(IllnessList illnessList)
        {
            _context.Add(illnessList);
        }

        public void AddVaccinationToDb(Vaccination vaccination)
        {
            _context.Add(vaccination);
        }

        public void AddVaccinationListToDb(VaccinationList vaccinationList)
        {
            _context.Add(vaccinationList);
        }

        public void UpdateDbIllness(Illness illness)
        {
            _context.Update(illness);
        }

        public void UpdateDbVaccination(Vaccination vaccination)
        {
            _context.Update(vaccination);
        }

        public void RemoveIllnessFromDb(Illness illness)
        {
            _context.Remove(illness);
        }

        public void RemoveVaccinationFromDb(Vaccination vaccination)
        {
            _context.Remove(vaccination);
        }

        public void SaveChangesToDb()
        {
            _context.SaveChanges();
        }

        public EntityEntry<Illness> getEntryIllness(Illness illness)
        {
            return _context.Entry(illness);
        }

        public EntityEntry<Vaccination> getEntryVaccination(Vaccination vaccination)
        {
            return _context.Entry(vaccination);
        }
    }
}
