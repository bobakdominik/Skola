using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("SKLAD_LIEKOV_ODDELENIA", Schema = "RAPSIK_SP")]
    public class DepartmentsMedicamentWarehouse
    {
        [Key][Column("ID_SKLADU")] 
        public int WarehouseId { get; set; }

        [Column("DATUM_EXPIRACIE")]
        public DateTime ExpirationDate { get; set; }

        [Column("KOD_LIEKU")]
        [ForeignKey("KOD_LIEKU")]
        public string MedicamentCode { get; set; }

        public Medicament Medicament { get; set; }

        [Column("ID_ODDELENIA")]
        [ForeignKey("ID_ODDELENIA")]
        public Department Department { get; set; }

        [Column("MNOZSTVO")] 
        public int Quantity { get; set; }

        [Column("MINIMALNE_MNOZSTVO")] 
        public int MinimalQuantity { get; set; }
    }
}
