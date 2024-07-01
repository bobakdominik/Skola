using medicinska_informatika_SP.Data.Models;
using Microsoft.AspNetCore.Identity;

namespace medicinska_informatika_SP.Data
{
    public class BcryptPasswordHasher : IPasswordHasher<Employee>
    {
        public string HashPassword(Employee user, string password)
        {
            return BCrypt.Net.BCrypt.HashPassword(password);
        }

        public PasswordVerificationResult VerifyHashedPassword(Employee user, string hashedPassword,
            string providedPassword)
        {
            if (BCrypt.Net.BCrypt.Verify(providedPassword, hashedPassword))
            {
                return PasswordVerificationResult.Success;
            }
            else
            {
                return PasswordVerificationResult.Failed;
            }
        }
    }
}