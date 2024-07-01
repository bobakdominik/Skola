using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("OCKOVANIE", Schema = "RAPSIK_SP")]
    public class Vaccination
    {
        [Key][Column("ID_VAKCINY")] 
        public int VaccinationId { get; set; }

        [Column("NAZOV_OCKOVANIA")] 
        public string VaccinationName { get; set; }

        [Column("TYP_OCKOVANIA")] 
        public string VaccinationType { get; set; }
    }
}
