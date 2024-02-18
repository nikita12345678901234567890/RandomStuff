using Microsoft.AspNetCore.Mvc;

using System;
using System.Collections.Generic;
using System.Linq;

namespace UpdateServer
{
    [ApiController]
    [Route("update")]
    public class UpdateController : ControllerBase
    {
        static string Latest = "0.0.1";
        static Dictionary<string, IUpdate> updates = new Dictionary<string, IUpdate>();

        [HttpGet("GetLatestVersion")]
        public string GetLatestVersion()
        {
            return Latest;
        }

        [HttpGet("GetLatestUpdate")]
        public IUpdate GetLatestUpdate()
        {
            return updates[Latest];
        }
    }
}
