let socket = WebSocket.prototype // 

const command = {
    state: () => ({
        voltage: 0,
        current: 0,
        power: 0,
        energy: 0,
        frequency: 0,
        pf: 0,

    }),
    mutations: {
        setVoltage: function (state, val) {
            state.voltage = val
        },
        setCurrent: function (state, val) {
            state.current = val
        },
        setPower: function (state, val) {
            state.power = val
        },
        setEnergy: function (state, val) {
            state.energy = val
        },
        setFrequency: function (state, val) {
            state.frequency = val
        },
        setPf: function (state, val) {
            state.pf = val
        },
    },
    actions: {
        initCommand: function (context) {
            // socket = new WebSocket('ws://' + '192.168.2.100' + ':81');
            socket = new WebSocket('ws://'+window.location.host+':81');
            socket.addEventListener('message', function (event) {
                let data = JSON.parse(event.data)
                if (data.pzemVoltage)
                    context.commit('setVoltage', data.pzemVoltage)
                if (data.pzemCurrent){

                    context.commit('setCurrent', data.pzemCurrent)
                }
                if (data.pzemPower){
                    context.commit('setPower', data.pzemPower)
                }
                if (data.pzemEnergy)
                    context.commit('setEnergy', data.pzemEnergy)
                if (data.pzemFrequency)
                    context.commit('setFrequency', data.pzemFrequency)
                if (data.pzemPf)
                    context.commit('setPf', data.pzemPf)
            });
        },


    },
    getters: {
        getVoltage: function (state) {
            return state.voltage
        },
        getCurrent: function (state) {
            return state.current
        },
        getPower: function (state) {
            return state.power
        },
        getEnergy: function (state) {
            return state.energy
        },
        getFrequency: function (state) {
            return state.frequency
        },
        getPf: function (state) {
            return state.pf
        },
    }
}
export default command
