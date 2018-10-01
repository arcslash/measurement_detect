// var isCameraON = false;//true when camera is on

console.log("[+]Scripts functional");
function measure(){
  console.log("[+]Console Requesting data");
  $.get('http://localhost:5000/measure',function(data){
    var fixed = data.replace(/\\/g,"");
    var fixed = fixed.substring(1, fixed.length-1);
    console.log("Fixed:" + fixed);
    var result = JSON.parse(fixed);
    
    // console.log(result);
    $('#measure_l').html(result['L']);
    $('#measure_l').addClass('badge-success');
    $('#measure_m').html(result['M']);
    $('#measure_n').html(result['N']);
    $('#measure_o').html(result['O']);
    $('#measure_p').html(result['P']);
    $('#measure_u').html(result['U']);
    $('#measure_k').html(result['K']);
    $("#result-image").attr("src","/media/ishara/Data/MAS/measurement_detection/new/core/outputs/draw1.jpg");
    $('#result-image').css('visibility', 'visible');
    $('#result-image').css('background-color', 'white');
    $('#result-image').css('visibility', 'visible');
    console.log(JSON.stringify(result))
    
    
    
    
      
  });

}

function test_table(){
  $('#measurements').append( '<tr>\
  <th>Bottom Margin</th>\
  <td>N/A</td>\
  <td>N/A</td>\
  <td>N/A</td>\
  <td>N/A</td>\
  <td>N/A</td>\
  <td>N/A</td>\
  <td>N/A</td>\
  <td>N/A</td>\
  </tr>' );
}

function test_pop_up(){
  $('#myModal').on('shown.bs.modal', function () {
    $('#myInput').trigger('focus')
  })
}


