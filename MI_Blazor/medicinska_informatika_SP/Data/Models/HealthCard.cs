using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("ZDRAVOTNA_KARTA", Schema = "RAPSIK_SP")]
    public class HealthCard
    {
        [Key][Column("ID_KARTY")] 
        public int CardId { get; set; }

        [Column("OS_CISLO_PACIENTA")]
        [ForeignKey("OS_CISLO_PACIENTA")]
        public int PatientId { get; set; }
    }
}
