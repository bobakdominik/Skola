using medicinska_informatika_SP.Data.Models;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;

namespace medicinska_informatika_SP.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
            Database.OpenConnection();
        }
        public DbSet<TestTabulka> TestTabulka { get; set; }

        public DbSet<DepartmentsMedicamentWarehouse> DepartmentsMedicamentWarehouses { get; set; }

        public DbSet<Department> Departments { get; set; }

        public DbSet<Machine> Machines { get; set; }

        public DbSet<Medicament> Medicaments { get; set; }

        public DbSet<MedicalInstrument> MedicalInstruments { get; set; }

        public DbSet<BlobData> BlobDatas { get; set; }

        public DbSet<Document> Documents { get; set; }

        public DbSet<Employee> Employee { get; set; }

        public new DbSet<Role> Roles { get; set; }

        public DbSet<Person> Persons { get; set; }

        public DbSet<Illness> Illnesses { get; set; }

        public DbSet<Vaccination> Vaccinations { get; set; }

        public DbSet<VaccinationList> VaccinationLists { get; set; }

        public DbSet<IllnessList> IllnessLists { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<DepartmentsMedicamentWarehouse>()
                .HasOne(w => w.Medicament)
                .WithMany(m => m.Records)
                .HasForeignKey(w => w.MedicamentCode);

            base.OnModelCreating(modelBuilder);
        }
    }
}