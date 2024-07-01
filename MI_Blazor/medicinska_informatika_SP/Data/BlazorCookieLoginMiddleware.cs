using Microsoft.AspNetCore.Identity;
using System.Collections.Concurrent;
using medicinska_informatika_SP.Data.Models;

namespace medicinska_informatika_SP.Data
{
    public class BlazorCookieLoginMiddleware<TUser> where TUser : class
    {
        #region Static Login Cache

        static IDictionary<Guid, LoginModel<TUser>> Logins { get; set; }
            = new ConcurrentDictionary<Guid, LoginModel<TUser>>();

        public static Guid AnnounceLogin(LoginModel<TUser> loginInfo)
        {
            loginInfo.LoginStarted = DateTime.Now;
            var key = Guid.NewGuid();
            Logins[key] = loginInfo;
            return key;
        }

        public static LoginModel<TUser> GetLoginInProgress(string key)
        {
            return GetLoginInProgress(Guid.Parse(key));
        }

        public static LoginModel<TUser> GetLoginInProgress(Guid key)
        {
            if (Logins.ContainsKey(key))
            {
                return Logins[key];
            }
            else
            {
                return null;
            }
        }

        #endregion

        private readonly RequestDelegate _next;

        public BlazorCookieLoginMiddleware(RequestDelegate next)
        {
            _next = next;
        }

        public async Task Invoke(HttpContext context, SignInManager<TUser> signInMgr)
        {
            if (context.Request.Path == "/login" && context.Request.Query.ContainsKey("key"))
            {
                var key = Guid.Parse(context.Request.Query["key"]);
                var info = Logins[key];

                var result = await signInMgr.PasswordSignInAsync(info.UserName, info.Password, info.RememberMe,
                    lockoutOnFailure: false);

                //Uncache password for security:
                info.Password = null;

                if (result.Succeeded)
                {
                    Logins.Remove(key);
                    context.Response.Redirect("/Kalendar");
                    return;
                }
                else if (result.RequiresTwoFactor)
                {
                    context.Response.Redirect("/loginwith2fa/" + key);
                    return;
                }
                else if (result.IsLockedOut)
                {
                    info.Error = "You are locked out. Please contact support.";
                }
                else
                {
                    info.Error = "Login failed. Check your username and password.";
                    await _next.Invoke(context);
                }
            }
            else if (context.Request.Path.StartsWithSegments("/logout"))
            {
                await signInMgr.SignOutAsync();
                context.Response.Redirect("/login");
                return;
            }

            //Continue http middleware chain:
            await _next.Invoke(context);
        }
    }
}