using medicinska_informatika_SP.Data.Constants;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("VOZIDLO", Schema = "RAPSIK_SP")]
    public class Vehicle
    {
        [Key][Column("ID_VOZIDLA")] 
        public int VehicleId { get; set; }

        [Column("ID_NEMOCNICE")]
        [ForeignKey("ID_NEMOCNICE")]
        public int HospitalId { get; set; }

        [Column("TYP_VOZIDLA")] 
        public VehicleType VehicleType { get; set; }

        [Column("KAPACITA")] 
        public int Capacity { get; set; }
    }
}
