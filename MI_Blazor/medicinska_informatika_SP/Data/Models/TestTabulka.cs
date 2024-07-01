using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("TEST", Schema = "RAPSIK_SP")]
    public class TestTabulka
    {
        [Key] [Column("CISLO")] public int Idecko { get; set; }
        [Column("MENO")] public string Meno { get; set; }
    }
}