async function pollDOM () {
    for(let i = 0; i< 30; i++){
        currentAlg.implementAction(currentAlg.insertElement.bind(currentAlg),i);
        await sleep(500);
    }
}
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}
pollDOM()