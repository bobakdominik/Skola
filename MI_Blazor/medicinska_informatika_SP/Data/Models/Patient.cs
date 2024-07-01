using medicinska_informatika_SP.Data.Constants;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("PACIENT", Schema = "RAPSIK_SP")]
    public class Patient
    {
        [Key][Column("OS_CISLO_PACIENTA")] 
        public int PatientId { get; set; }

        [Column("ROD_CISLO")]
        [ForeignKey("ROD_CISLO")]
        public string IdentificationNumber { get; set; }

        [Column("ID_NEMOCNICE")]
        [ForeignKey("ID_NEMOCNICE")]
        public string HospitalId { get; set; }

        [Column("KRVNA_SKUPINA")] 
        public BloodType BloodType { get; set; }
    }
}
