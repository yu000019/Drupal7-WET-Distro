 var params = {
    zebra:{selector:'.zebra'},
     tabs: {
        "tabs": encodeURIComponent('[ \
            {"tabSelector":"#tab-container1", "defaultTab":"li:nth-child(2)", "autoHeight":true, "cycle":3000}, \
            {"tabSelector":"#tab-container2", "defaultTab":"li:nth-child(1)", "autoHeight":true, "cycle":2000}, \
        ]')
    },
    menubar:{},
    multimedia:{}
};
PE.progress(params);
