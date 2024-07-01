using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("OSOBA", Schema = "RAPSIK_SP")]
    public class Person
    {
        [Key][Column("ROD_CISLO")] 
        public string IdentificationNumber { get; set; }

        [Column("MENO")] 
        public string Name { get; set; }

        [Column("PRIEZVISKO")] 
        public string Surname { get; set; }

        [Column("PSC")] 
        public string PostCode { get; set; }

        [Column("ULICA")] 
        public string Street { get; set; }
    }
}
