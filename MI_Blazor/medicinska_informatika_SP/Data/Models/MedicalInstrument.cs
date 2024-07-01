using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("MEDICINSKY_NASTROJ", Schema = "RAPSIK_SP")]
    public class MedicalInstrument
    {
        [Key][Column("ID_NASTROJA")] 
        public int InstrumentId { get; set; }

        [Column("ID_ODDELENIA")]
        [ForeignKey("ID_ODDELENIA")]
        public Department Department { get; set; }

        [Column("NAZOV_NASTROJA")] 
        public string InstrumentName { get; set; }

        [Column("ZIVOTNOST")] 
        public DateTime ServiceLife { get; set; }
    }
}
