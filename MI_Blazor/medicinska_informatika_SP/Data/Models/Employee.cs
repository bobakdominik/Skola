using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("PERSONAL", Schema = "RAPSIK_SP")]
    public class Employee
    {
        [Key][Column("OS_CISLO_PERSONALU")] 
        public int EmployeeId { get; set; }

        [Column("ROD_CISLO")]
        [ForeignKey("ROD_CISLO")]
        public string IdentificationNumber { get; set; }

        [Column("ID_ODDELENIA")]
        [ForeignKey("ID_ODDELENIA")]
        public int DepartmentId { get; set; }

        [Column("TYP_PRACE")] 
        public string WorkType { get; set; }

        [Column("DATUM_OD")] 
        public DateTime DateFrom { get; set; }

        [Column("DATUM_DO")] 
        public DateTime? DateTo { get; set; }

        [Column("POUZIVATELSKE_MENO")] 
        public string? Username { get; set; }

        [Column("HESLO")] 
        public string? Password { get; set; }
    }
}
