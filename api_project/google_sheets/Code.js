var sheet_id = "1N_N6rpL2gMV4EzobMDcBjyO1cNSFTd66P7dTJlxY9ns"

function doGet(e) {
  // Safety: make sure we got parameters
  if (!e || !e.parameter || !e.parameter.key) {
    return ContentService
      .createTextOutput("Missing 'key' parameter")
      .setMimeType(ContentService.MimeType.TEXT);
  }

  // "rgb" or "led"
  var key = e.parameter.key;   
  var ss  = SpreadsheetApp.openById(sheet_id);
  var date_time = new Date();

  if (key === "rgb") {
    // Expect: ?key=rgb&r=123&g=45&b=67
    var r = e.parameter.r;
    var g = e.parameter.g;
    var b = e.parameter.b;

    var sheetRgb = ss.getSheetByName("rgb"); // columns: Date | R | G | B
    sheetRgb.appendRow([date_time, r, g, b]);

    return ContentService
      .createTextOutput("OK rgb")
      .setMimeType(ContentService.MimeType.TEXT);

  } else if (key === "led") {
    // Expect: ?key=led&state=on  (or off)
    var state = e.parameter.state;

    var sheetLed = ss.getSheetByName("led"); // columns: Date | State
    sheetLed.appendRow([date_time, state]);

    return ContentService
      .createTextOutput("OK led")
      .setMimeType(ContentService.MimeType.TEXT);

  } else {
    // Unknown key
    return ContentService
      .createTextOutput("Unknown key: " + key)
      .setMimeType(ContentService.MimeType.TEXT);
  }
}
