using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("PRISTROJ", Schema = "RAPSIK_SP")]
    public class Machine
    {
        [Key][Column("ID_PRISTROJA")] 
        public int MachineId { get; set; }

        [Column("ID_ODDELENIA")]
        [ForeignKey("ID_ODDELENIA")]
        public Department Department { get; set; }

        [Column("NAZOV_PRISTROJA")] 
        public string MachineName { get; set; }

        [Column("STAV")] 
        public char State { get; set; }

        [Column("SERVIS")] 
        public DateTime? Service { get; set; }
    }
}
