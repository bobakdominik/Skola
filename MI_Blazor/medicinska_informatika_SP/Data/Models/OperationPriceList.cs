using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("CENNIK_UKONOV", Schema = "RAPSIK_SP")]
    public class OperationPriceList
    {
        [Key][Column("ID_UKONU")] 
        public int OperationId { get; set; }

        [Key][Column("DATUM_OD")] 
        public DateTime DateFrom { get; set; }

        [Column("CENA")] 
        public int Price { get; set; }

        [Column("DATUM_DO")] 
        public DateTime? DateTo { get; set; }
    }
}
