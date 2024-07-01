using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("ZABRATE_LOZKA", Schema = "RAPSIK_SP")]
    public class OccupiedBeds
    {
        [Key][Column("OS_CISLO_PACIENTA")]
        public int PatientId { get; set; }

        [Key][Column("CISLO_LOZKA")]
        public int BedNumber { get; set; }

        [Key][Column("DATUM_OD")] 
        public DateTime DateFrom { get; set; }

        [Column("DATUM_DO")] 
        public DateTime? DateTo { get; set; }
    }
}
