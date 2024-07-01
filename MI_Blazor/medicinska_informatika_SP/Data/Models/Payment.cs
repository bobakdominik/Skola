using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("PLATBA", Schema = "RAPSIK_SP")]
    public class Payment
    {
        [Key][Column("ID_PLATBY")] 
        public int PaymentId { get; set; }

        [Column("ID_UKONU")]
        [ForeignKey("ID_UKONU")]
        public int OperationId { get; set; }

        [Column("SUMA")] 
        public int Sum { get; set; }

        [Column("DATUM_PLATBY")] 
        public DateTime PaymentDate { get; set; }
    }
}
