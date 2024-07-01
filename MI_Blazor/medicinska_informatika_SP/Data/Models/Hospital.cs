using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("NEMOCNICA", Schema = "RAPSIK_SP")]
    public class Hospital
    {
        [Key][Column("ID_NEMOCNICE")] 
        public int HospitalId { get; set; }

        [Column("NAZOV_NEMOCNICE")] 
        public string HospitalName { get; set; }

        [Column("PSC")] 
        public string PostCode { get; set; }

        [Column("ULICA")] 
        public string Street { get; set; }
    }
}
