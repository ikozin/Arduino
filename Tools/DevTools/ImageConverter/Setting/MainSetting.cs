using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace ImageConverter.Setting
{
    public class MainSetting
    {
        public MainSetting()
        {
            Font = "Cascadia Mono; 9";
        }

        [JsonRequired]
        [JsonPropertyName("font")]
        public required string Font { get; set; }
    }
}
