function rgbToHsv(rgb) {
    // RGBå½¢å¼ã®æ–‡å­—åˆ—ã‚’R,G,Bã«åˆ†è§£ï¼ˆeg. #FF0000->1,0,0ï¼‰
    const r = parseInt(rgb.substring(1, 3), 16) / 255;
    const g = parseInt(rgb.substring(3, 5), 16) / 255;
    const b = parseInt(rgb.substring(5, 7), 16) / 255;

    // RGBå€¤ã‚’ç”¨ã„ã¦HSVå€¤ã‚’è¨ˆç®—
    const max = Math.max(r, g, b);
    const min = Math.min(r, g, b);
    const diff = max - min;

    let h = 0;
    let s = 0;
    let v = max;

    if (diff > 0) {
        if (max === r) {
            h = (60 * ((g - b) / diff) + 360) % 360;
        } else if (max === g) {
            h = (60 * ((b - r) / diff) + 120) % 360;
        } else {
            h = (60 * ((r - g) / diff) + 240) % 360;
        }
        s = diff / max;
    }

    return { h, s, v };
}


function showColors() {
    var input = document.getElementById("color-input");
    var colors = input.value.split(",");
    input.style.display = "none";
    // var numColumns = parseInt(document.getElementById("num-columns").value);

    var numColumns = 6;
    var colorList = document.getElementById("color-list");
    colorList.innerHTML = "";
    var row;
    for (var i = 0; i < colors.length; i++) {
        var color = colors[i].trim();
        if (color.charAt(0) !== "#") {
            color = "#" + color;
        }
        if (color.length > 7) {
            color = color.substr(0, 7);
        }

        var div = document.createElement("div");
        div.className = "color-box";
        div.style.backgroundColor = color;

        var inner_div = document.createElement("div");
        inner_div.className = "hex-code";
        inner_div.innerText = color;

        if (rgbToHsv(color)["v"] < 0.5) {
            inner_div.style.color = "#ddd";
            inner_div.style.fontWeight = "normal";
        }
        div.appendChild(inner_div);

        if (i % numColumns === 0) {
            row = document.createElement("div");
            row.className = "color-box-row"
            colorList.appendChild(row);
        }
        row.appendChild(div);
    }
}

window.onload = function () {
    showColors();
};
