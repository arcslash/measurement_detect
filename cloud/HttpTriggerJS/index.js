var azure = require('azure-storage');
var account_name = "measure-table";
var primary_key = "27lfAYsjLCDdnTUCE1m1Dha9lCY5VlAdPGBsFq5QWiFkyp7IFXp5zf8OQxG6OMx5Bcqg10hDHbw66FxpoZ0tSA==";
var end_point = "https://measure-table.table.cosmosdb.azure.com:443/";
var tableSvc = azure.createTableService(account_name, primary_key, end_point);
var entGen = azure.TableUtilities.entityGenerator;



// handle the http request
module.exports = function (context, req) {
    if (req.query.style_code || (req.body && req.body.style_code)) {
        if (typeof req.query.style_code != "undefined") {
            // tableSvc.createTableIfNotExists('styles', function(error, result, response){
            //     if(!error){  
            //         context.res = {
                       
            //             body: "success: "+result
            //         };                
            //     }
            //   });
            //   var style = {
            //     PartitionKey: {'_':'kreeda'},
            //     RowKey: {'_': 1},
            //     style_code: {'_':req.query.style_code},
            //     customer: {'_':req.query.customer},
            //     front_panel: {'_':req.query.front_panel},
            //     back_panel: {'_':req.query.back_panel}
            //   };

            //   tableSvc.insertEntity('styles',style, function (error, result, response) {
            //     if(!error){
            //         context.res = {
                       
            //             body: "success: "+result
            //         };
            //     }
            //   });

              context.res = {
                       
                body: "success: "
            };

        
        }
        else {
            // context.log("Processing user info from request body...");
            // res = ProcessNewUserInformation(context, req.body.name, req.body.address);
        }
    }else {
        context.res = {
            status: 400,
            body: { error: 'You gotta ping to pong'}
        };
    }
    context.done();  
    
          


};