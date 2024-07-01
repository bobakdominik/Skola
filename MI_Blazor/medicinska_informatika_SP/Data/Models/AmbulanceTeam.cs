using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("VYJAZDOVY_TIM", Schema = "RAPSIK_SP")]
    public class AmbulanceTeam
    {
        [Key][Column("ID_VOZIDLA")] 
        public int VehicleId { get; set; }

        [Key][Column("OS_CISLO_PERSONALU")] 
        public int EmployeeId { get; set; }
    }
}
