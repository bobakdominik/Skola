using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("ZOZNAM_ROL", Schema = "RAPSIK_SP")]
    public class Role
    {
        [Key][Column("ID_ROLA")]
        public int IDRola { get; set; }

        [Column("OS_CISLO_PERSONALU")]
        [ForeignKey("OS_CISLO_PERSONALU")]
        public int Personal { get; set; }
    }
}
