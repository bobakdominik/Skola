using Microsoft.AspNetCore.Identity;
using Microsoft.Extensions.Configuration;
using System.Data.SqlClient;
using System.Threading;
using System.Threading.Tasks;
using medicinska_informatika_SP.Data.Models;
using Microsoft.Data.SqlClient;

namespace medicinska_informatika_SP.Data
{
    public class RoleStore : IRoleStore<Role>
    {
        private readonly IRoleService _roleService;

        public RoleStore(IRoleService roleService)
        {
            _roleService = roleService;
        }

        public async Task<IdentityResult> CreateAsync(Role role, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return IdentityResult.Success;
        }

        public async Task<IdentityResult> UpdateAsync(Role role, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return IdentityResult.Success;
        }

        public async Task<IdentityResult> DeleteAsync(Role role, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return IdentityResult.Success;
        }

        public Task<string> GetRoleIdAsync(Role role, CancellationToken cancellationToken)
        {
            return Task.FromResult(role.IDRola.ToString());
        }

        public Task<string> GetRoleNameAsync(Role role, CancellationToken cancellationToken)
        {
            return Task.FromResult(role.Personal.ToString());
        }

        public Task SetRoleNameAsync(Role role, string roleName, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public Task<string> GetNormalizedRoleNameAsync(Role role, CancellationToken cancellationToken)
        {
            return Task.FromResult(role.Personal.ToString());
        }

        public Task SetNormalizedRoleNameAsync(Role role, string normalizedName, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public async Task<Role> FindByIdAsync(string roleId, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return _roleService.GetRoleByID(Convert.ToInt32(roleId));
        }

        public async Task<Role> FindByNameAsync(string normalizedRoleName, CancellationToken cancellationToken)
        {
            cancellationToken.ThrowIfCancellationRequested();
            return null;
        }

        public void Dispose()
        {
        }
    }
}