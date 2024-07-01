using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Reflection.Metadata;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("BLOB_DATA", Schema = "RAPSIK_SP")]
    public class BlobData
    {
        [Key][Column("ID_DOKUMENTU")] 
        public int DocumentId { get; set; }

        [Column("ID_SUBORU")] 
        public int FileId { get; set; }

        [Column("DATA")] 
        public byte[] Data { get; set; }
    }
}
