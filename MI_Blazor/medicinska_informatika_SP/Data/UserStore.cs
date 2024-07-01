using Microsoft.AspNetCore.Identity;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using medicinska_informatika_SP.Data.Models;

namespace medicinska_informatika_SP.Data
{
    public class UserStore : IUserEmailStore<Employee>, IUserPhoneNumberStore<Employee>,
        IUserTwoFactorStore<Employee>, IUserPasswordStore<Employee>, IUserRoleStore<Employee>
    {
        private readonly IEmployeService _employeService;
        private readonly IRoleService _roleService;

        public UserStore(
            IEmployeService employeService, IRoleService roleService)
        {
            _employeService = employeService;
            _roleService = roleService;
        }

        public async Task<IdentityResult> CreateAsync(Employee user, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return IdentityResult.Success;
        }

        public async Task<IdentityResult> DeleteAsync(Employee user, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();

            return IdentityResult.Success;
        }

        public async Task<Employee> FindByIdAsync(string userId, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return _employeService.GetEmployeeByID(Convert.ToInt32(userId));
        }

        public async Task<Employee> FindByNameAsync(string username, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return _employeService.GetEmployeeByName(username);
        }

        public Task<string> GetNormalizedUserNameAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(user.Username);
        }

        public Task<string> GetUserIdAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(user.EmployeeId.ToString());
        }

        public Task<string> GetUserNameAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(user.Username);
        }

        public Task SetNormalizedUserNameAsync(Employee user, string normalizedName,
            CancellationToken cancellationToken)
        {
            //user.NormalizedUserName = normalizedName;
            return Task.FromResult(0);
        }

        public Task SetUserNameAsync(Employee user, string userName, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public async Task<IdentityResult> UpdateAsync(Employee user, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return IdentityResult.Success;
        }

        public Task SetEmailAsync(Employee user, string email, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public Task<string> GetEmailAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(string.Empty);
        }

        public Task<bool> GetEmailConfirmedAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(false);
        }

        public Task SetEmailConfirmedAsync(Employee user, bool confirmed, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public async Task<Employee> FindByEmailAsync(string normalizedEmail, CancellationToken cancellationToken)
        {
            return _employeService.GetEmployeeByName(normalizedEmail);
        }

        public Task<string> GetNormalizedEmailAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(string.Empty);
        }

        public Task SetNormalizedEmailAsync(Employee user, string normalizedEmail, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public Task SetPhoneNumberAsync(Employee user, string phoneNumber, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public Task<string> GetPhoneNumberAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult("phone number");
        }

        public Task<bool> GetPhoneNumberConfirmedAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(true);
        }

        public Task SetPhoneNumberConfirmedAsync(Employee user, bool confirmed, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public Task SetTwoFactorEnabledAsync(Employee user, bool enabled, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public Task<bool> GetTwoFactorEnabledAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(false);
        }

        public Task SetPasswordHashAsync(Employee user, string passwordHash, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public Task<string> GetPasswordHashAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(user.Password);
        }

        public Task<bool> HasPasswordAsync(Employee user, CancellationToken cancellationToken)
        {
            return Task.FromResult(user.Password != null);
        }

        public async Task AddToRoleAsync(Employee user, string roleName, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
        }

        public async Task RemoveFromRoleAsync(Employee user, string roleName, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
        }

        public async Task<IList<string>> GetRolesAsync(Employee user, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();

            var role = _roleService.GetRoleForUser(user);
            return new List<string>()
            {
                role.IDRola.ToString()
            };
        }

        public async Task<bool> IsInRoleAsync(Employee user, string roleName, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            var role = _roleService.GetRoleForUser(user).IDRola.ToString();
            return role == roleName;
        }

        public async Task<IList<Employee>> GetUsersInRoleAsync(string roleName, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return null;
        }

        public void Dispose()
        {
        }
    }
}