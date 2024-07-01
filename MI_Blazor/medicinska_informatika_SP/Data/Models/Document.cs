using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("DOKUMENT", Schema = "RAPSIK_SP")]
    public class Document
    {
        [Key][Column("ID_DOKUMENTU")] 
        public int DocumentId { get; set; }

        [Column("ID_KARTY")]
        [ForeignKey("ID_KARTY")]
        public int CardId { get; set; }

        [Column("ID_ODDELENIA")]
        [ForeignKey("ID_ODDELENIA")]
        public int DepartmentId { get; set; }

        [Column("TYP_DOKUMENTU")] 
        public string DocumentType { get; set; }

        [Column("FORMAT")] 
        public string DocumentFormat { get; set; }

        [Column("NAZOV_DOKUMENTU")] 
        public string DocumentName { get; set; }

        [Column("DATUM_VYSTAVENIA")] 
        public DateTime IssueDate { get; set; }
    }
}
