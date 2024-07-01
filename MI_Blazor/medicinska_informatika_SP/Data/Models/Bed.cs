using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("LOZKO", Schema = "RAPSIK_SP")]
    public class Bed
    {
        [Key][Column("CISLO_LOZKA")] 
        public int BedNumber { get; set; }

        [Column("ID_ODDELENIA")]
        [ForeignKey("ID_ODDELENIA")]
        public int DepartmentId { get; set; }
    }
}
