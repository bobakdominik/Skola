using medicinska_informatika_SP.Data.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using System.Data.Common;

namespace medicinska_informatika_SP.Data
{
    public class WarehouseService
    {
        private readonly ApplicationDbContext _context;

        public WarehouseService(ApplicationDbContext context)
        {
            _context = context;
        }

        public DbConnection getDbConnection()
        {
            return _context.Database.GetDbConnection();
        }

        public async Task<IEnumerable<Machine>> GetMachines()
        {
            return await _context.Machines.Include(machine => machine.Department).ToListAsync();
        }

        public async Task<IEnumerable<MedicalInstrument>> GetMedicalInstruments()
        {
            return await _context.MedicalInstruments.Include(machine => machine.Department).ToListAsync();
        }

        public async Task<IEnumerable<Medicament>> GetMedicaments()
        {
            return await _context.Medicaments.ToListAsync();
        }

        public async Task<IEnumerable<DepartmentsMedicamentWarehouse>> GetDepartmentsMedicamentWarehouse()
        {
            return await _context.DepartmentsMedicamentWarehouses
                .Include(machine => machine.Department)
                .Include(machine => machine.Medicament)
                .ToListAsync();
        }

        public void AddToDb(MedicalInstrument instrument)
        {
            _context.Add(instrument);
        }

        public void AddMachineToDb(Machine machine)
        {
            _context.Add(machine);
        }

        public void AddMedicamentToDb(Medicament medicament)
        {
            _context.Add(medicament);
        }

        public void AddDepartmentsMedicamentWarehouseToDb(DepartmentsMedicamentWarehouse departmentsMedicamentWarehouse)
        {
            _context.Add(departmentsMedicamentWarehouse);
        }

        public void UpdateDb(MedicalInstrument instrument)
        {
            _context.Update(instrument);
        }

        public void UpdateDbMachine(Machine machine)
        {
            _context.Update(machine);
        }

        public void UpdateDbMedicament(Medicament medicament)
        {
            _context.Update(medicament);
        }

        public void UpdateDbDepartmentsMedicamentWarehouse(DepartmentsMedicamentWarehouse departmentsMedicamentWarehouse)
        {
            _context.Update(departmentsMedicamentWarehouse);
        }

        public void RemoveFromDb(MedicalInstrument instrument)
        {
            _context.Remove(instrument);
        }

        public void RemoveMachineFromDb(Machine machine)
        {
            _context.Remove(machine);
        }

        public void RemoveMedicamentFromDb(Medicament medicament)
        {
            _context.Remove(medicament);
        }

        public void RemoveDepartmentsMedicamentWarehouseFromDb(DepartmentsMedicamentWarehouse departmentsMedicamentWarehouse)
        {
            _context.Remove(departmentsMedicamentWarehouse);
        }

        public void SaveChangesToDb()
        {
            _context.SaveChanges();
        }

        public EntityEntry<MedicalInstrument> getEntry(MedicalInstrument instrument)
        {
            return _context.Entry(instrument);
        }

        public EntityEntry<Machine> getEntryMachine(Machine machine)
        {
            return _context.Entry(machine);
        }

        public EntityEntry<Medicament> getEntryMedicament(Medicament medicament)
        {
            return _context.Entry(medicament);
        }

        public EntityEntry<DepartmentsMedicamentWarehouse> getEntryDepartmentsMedicamentWarehouse(DepartmentsMedicamentWarehouse departmentsMedicamentWarehouse)
        {
            return _context.Entry(departmentsMedicamentWarehouse);
        }
    }
}