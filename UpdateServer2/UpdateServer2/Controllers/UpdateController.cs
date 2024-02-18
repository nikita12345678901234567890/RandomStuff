using Microsoft.AspNetCore.Mvc;

namespace UpdateServer2.Controllers
{
    public class UpdateController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
