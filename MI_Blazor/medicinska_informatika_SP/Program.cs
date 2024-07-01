// using medicinska_informatika_SP.Areas.Identity;

using medicinska_informatika_SP.Data;
using medicinska_informatika_SP.Data.Models;
using Microsoft.AspNetCore.Components.Authorization;
using Microsoft.AspNetCore.Components.Server;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using Radzen;
using medicinska_informatika_SP.Areas.Identity;

namespace medicinska_informatika_SP
{
    public class Program
    {
        public static WebApplicationBuilder builder;

        public static void Main(string[] args)
        {
            builder = WebApplication.CreateBuilder(args);
            // Add services to the container.
            builder.Services.AddScoped<DialogService>();
            builder.Services.AddScoped<NotificationService>();
            builder.Services.AddScoped<TooltipService>();
            builder.Services.AddScoped<ContextMenuService>();
            var connectionString = builder.Configuration.GetConnectionString("DefaultConnection") ??
                                   throw new InvalidOperationException(
                                       "Connection string 'DefaultConnection' not found.");
            builder.Services.AddDbContext<ApplicationDbContext>(options =>
                options.UseOracle(connectionString));
            builder.Services.AddDatabaseDeveloperPageExceptionFilter();
            builder.Services.AddRazorPages();
            builder.Services.AddServerSideBlazor();
            //Kazdy serice musim pridat do builder
            builder.Services.AddScoped<TestujemeService>();
            builder.Services.AddScoped<WarehouseService>();
            builder.Services.AddScoped<PDSOutputsService>();
            builder.Services.AddScoped<PatientCardsService>();
            builder.Services.AddScoped<IEmployeService, EmployeService>();
            builder.Services.AddScoped<IRoleService, RoleService>();

            builder.Services.AddTransient<IUserStore<Employee>, medicinska_informatika_SP.Data.UserStore>();
            builder.Services.AddTransient<IRoleStore<Role>, medicinska_informatika_SP.Data.RoleStore>();
            builder.Services.AddTransient<IPasswordHasher<Employee>, BcryptPasswordHasher>();
            builder.Services
                .AddScoped<AuthenticationStateProvider, RevalidatingIdentityAuthenticationStateProvider<Employee>>();

            builder.Services.AddIdentity<Employee, Role>()
                .AddDefaultTokenProviders()
                .AddRoleManager<RoleManager<Role>>()
                .AddSignInManager<SignInManager<Employee>>();

            var app = builder.Build();

            // Configure the HTTP request pipeline.
            if (app.Environment.IsDevelopment())
            {
                app.UseMigrationsEndPoint();
            }
            else
            {
                app.UseExceptionHandler("/Error");
                // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
                app.UseHsts();
            }

            app.UseHttpsRedirection();

            app.UseStaticFiles();

            app.UseRouting();

            app.UseAuthentication();
            app.UseAuthorization();
            app.UseMiddleware<BlazorCookieLoginMiddleware<Employee>>();

            app.MapControllers();
            app.MapBlazorHub();
            app.MapFallbackToPage("/_Host");

            app.Run();
        }
    }
}