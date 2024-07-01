using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("LEKARSKY_UKON", Schema = "RAPSIK_SP")]
    public class MedicalOperation
    {
        [Key][Column("ID_UKONU")] 
        public int OperationId { get; set; }

        [Column("ID_KARTY")]
        [ForeignKey("ID_KARTY")]
        public int CardId { get; set; }

        [Column("ID_ODDELENIA")]
        [ForeignKey("ID_ODDELENIA")]
        public int DepartmentId { get; set; }

        [Column("DATUM_VYKONANIA")] 
        public DateTime ExecutionDate { get; set; }

        [Column("NAZOV_UKONU")] 
        public string OperationName { get; set; }

        [Column("POPIS")] 
        public string? Description { get; set; }
    }
}
