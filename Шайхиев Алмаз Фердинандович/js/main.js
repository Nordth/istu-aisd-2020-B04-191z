$(document).ready(function(){          
            $(".add_offer").click(function() {
                $.ajax({  
                    type: "get",  
                    url: "show_offers_table.php",  
                    data: $(".offers").serialize(), 
                    success: function(html){  
                        $(".show_offers_table").html(html);  
                    }  
                });  
                return false;  
            });  
              
        });  
        
