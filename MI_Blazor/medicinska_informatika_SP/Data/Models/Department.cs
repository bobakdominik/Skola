using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("ODDELENIE", Schema = "RAPSIK_SP")]
    public class Department
    {
        [Key][Column("ID_ODDELENIA")] 
        public int DepartmentId { get; set; }

        [Column("ID_NEMOCNICE")]
        [ForeignKey("ID_NEMOCNICE")]
        public int HospitalId { get; set; }

        [Column("NAZOV_ODDELENIA")] 
        public string DepartmentName { get; set; }

        [Column("TYP_ODDELENIA")] 
        public string DepartmentType { get; set; }

        [Column("ZMENA_OD")] 
        public DateTime? ShiftFrom { get; set; }

        [Column("ZMENA_DO")] 
        public DateTime? ShiftTo { get; set; }
    }
}
