using Microsoft.AspNetCore.Mvc;

namespace UpdateServer2.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class UpdateController : Controller
    {
        decimal currentVer = 5;

        Dictionary<decimal, Action> updates;

        public UpdateController()
        {
            updates = new Dictionary<decimal, Action>();

            updates.Add(1, );
        }

        [HttpGet("GetVersion")]
        public decimal GetVersion()
        {
            return currentVer;
        }

        [HttpGet("GetUpdate/{version}")]
        public string GetUpdate(decimal version)
        {
            return $"Hi{version}";
        }
    }
}
