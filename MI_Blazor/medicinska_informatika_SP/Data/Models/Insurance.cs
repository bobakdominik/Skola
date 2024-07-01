using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("POISTENIE", Schema = "RAPSIK_SP")]
    public class Insurance
    {
        [Key][Column("OS_CISLO_PACIENTA")] 
        public int PatientId { get; set; }

        [Column("TYP_POISTENIA")] 
        public string InsuranceType { get; set; }

        [Key][Column("DATUM_OD")] 
        public DateTime DateFrom { get; set; }

        [Column("DATUM_DO")] 
        public DateTime? DateTo { get; set; }
    }
}
