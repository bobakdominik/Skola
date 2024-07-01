using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("CHOROBA", Schema = "RAPSIK_SP")]
    public class Illness
    {
        [Key][Column("ID_CHOROBY")] 
        public int IllnessId { get; set; }

        [Column("NAZOV_CHOROBY")]
        public string IllnessName { get; set; }

        [Column("KOD_CHOROBY")] 
        public string IllnessCode { get; set; }
    }
}
